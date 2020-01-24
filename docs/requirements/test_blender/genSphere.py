import bpy
import bmesh

bpyscene = bpy.context.scene

import time

aimPoly =10000

for i in range(10):
    start = time.time()

    #Delete the actual object
    bpy.ops.object.delete() 
    
    # Create an empty mesh and the object.
    mesh = bpy.data.meshes.new('Basic_Sphere')
    basic_sphere = bpy.data.objects.new("Basic_Sphere", mesh)

    # Add the object into the scene.
    bpyscene.objects.link(basic_sphere)
    bpyscene.objects.active = basic_sphere
    basic_sphere.select = True

    # Construct the bmesh sphere and assign it to the blender mesh.
    bm = bmesh.new()

    #UVSphere
    #bmesh.ops.create_uvsphere(bm, u_segments=32, v_segments=16, diameter=1)

    #Icosphere
    bmesh.ops.create_icosphere(bm, subdivisions=i, diameter=1)
    bm.to_mesh(mesh)
    bm.free()

    end = time.time()

    #Stats
    print("\nGenerated mesh :")
    print(i, "Parameter")
    print(end - start, "s")
    print(len(mesh.polygons), "polygons")
    print(len(mesh.edges), "edges")
    print(len(mesh.vertices), "vertices")

    #Limit
    if(len(mesh.polygons) > aimPoly):
        break
