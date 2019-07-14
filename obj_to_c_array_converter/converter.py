import re
from collections import defaultdict

import numpy as np

with open("in.obj", "r", encoding="utf-8") as file:
    data = file.readlines()

    vs, vns, fs, fns = [], [], [], []
    for line in data:
        line = line.strip()
        v = re.findall(r"v\s+(-*\d+.\d+)\s+(-*\d+.\d+)\s+(-*\d+.\d+)\s*", line)
        vn = re.findall(r"vn\s+(-*\d+.\d+)\s+(-*\d+.\d+)\s+(-*\d+.\d+)\s*", line)
        f = re.findall(r"f\s+(\d+)//(\d+)\s+(\d+)//(\d+)\s+(\d+)//(\d+)\s*", line)

        if len(v) != 0:
            vv = v[0]
            vs.append([float(vv[0]), float(vv[1]), float(vv[2])])

        if len(vn) != 0:
            vvn = vn[0]
            vns.append([float(vvn[0]), float(vvn[1]), float(vvn[2])])

        if len(f) != 0:
            index = f[0]
            fs.append([int(index[0]), int(index[2]), int(index[4])])
            fns.append([int(index[1]), int(index[3]), int(index[5])])

    scale = 32768
    scale /= 2
    scale -= 1

    max_ver_x = max([v[0] for v in vs])
    max_ver_y = max([v[1] for v in vs])
    max_ver_z = max([v[2] for v in vs])

    maxx = max(max_ver_x, max_ver_y) / 1.2

    rescaled_vs = [(
        int(scale * v[0] / maxx),
        int(scale * v[1] / maxx),
        int(scale * v[2] / maxx)
    )
        for v in vs]


    def normalize(normal):
        len = np.linalg.norm(normal)
        return normal[0] / len, normal[1] / len, normal[2] / len


    vns = [normalize(vn) for vn in vns]

    vns = [[int(vn_el * 32767) for vn_el in vn] for vn in vns]  # temporarily scale normals to 0 to 255

    print(min([min(vn) for vn in rescaled_vs]))
    print(max([max(vn) for vn in rescaled_vs]))

    # apply indices table for positions and normals

    vertices = []
    for f in fs:
        vertices.append(rescaled_vs[f[0] - 1])
        vertices.append(rescaled_vs[f[1] - 1])
        vertices.append(rescaled_vs[f[2] - 1])

    for i, fn in enumerate(fns):
        vertices[3 * i] = vertices[3 * i], tuple(vns[fn[0] - 1])
        vertices[3 * i + 1] = vertices[3 * i + 1], tuple(vns[fn[1] - 1])
        vertices[3 * i + 2] = vertices[3 * i + 2], tuple(vns[fn[2] - 1])

    old_size = 2 * len(vertices * 6)
    print("size before compression:", old_size, "bytes")

    # optimize vertices creating new indices table

    elements = defaultdict(list)

    for i, v in enumerate(vertices):
        elements[v].append(i)

    indices = [None] * len(vertices)

    vertices_result = []
    for vertex, num_list in elements.items():
        vertices_result.append(vertex)
        id = len(vertices_result) - 1
        for num in num_list:
            indices[num] = id

    # group indices - faces

    indices_result = []
    for i in range(0, int(len(indices) / 3)):
        indices_result.append((
            indices[3 * i],
            indices[3 * i + 1],
            indices[3 * i + 2]
        ))

    new_size = 2 * (len(vertices_result) * 6 + len(indices_result) * 3)
    print("size after compression:", new_size, "bytes")
    # print("compression ratio: {0:.2f}%".format(new_size / old_size * 100.0))

    with open("mesh.h", "w", encoding="utf-8") as f:

        print("#include \"definitions.h\"", file=f)
        print(file=f)
        print("#ifndef MESH_H", file=f)
        print("#define MESH_H", file=f)
        print(file=f)
        print("const uint16_t num_vertices = {};".format(len(vertices_result)), file=f)
        print("const uint16_t num_indices = {};".format(len(indices_result)), file=f)
        print(file=f)

        print("const vertex_attr_t vertices[] = {", file=f)
        print("\t", end="", file=f)
        for i, v in enumerate(vertices_result):
            print("VA({},{},{},{},{},{}){}".format(
                v[0][0], v[0][1], v[0][2],
                v[1][0], v[1][1], v[1][2],
                ", " if i != len(vertices_result) - 1 else ""),
                end="", file=f)
            if (i + 1) % 3 == 0 and i != 0:
                print("\n\t", end="", file=f)
        print("\n};", file=f)
        print(file=f)

        print("const triangle_index_t indices[] = {", file=f)
        print("\t", end="", file=f)
        for i, index in enumerate(indices_result):
            print("IDX({},{},{}){}".format(
                index[0], index[1], index[2],
                ", " if i != len(indices_result) - 1 else ""),
                end="", file=f)
            if (i + 1) % 5 == 0 and i != 0:
                print("\n\t", end="", file=f)
        print("\n};\n", file=f)
        print("#endif // MESH_H", file=f)
