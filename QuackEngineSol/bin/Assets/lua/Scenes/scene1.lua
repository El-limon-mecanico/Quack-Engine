scene1 = {
    entities = {"entidad1", "entidad2"}
}

entidad1 = {
    Components = {"MeshRenderer", "Transform","Rigidbody", "Prueba"},

    MeshRenderer = {
        Mesh = "Suzanne.mesh",
        Position = {0,500,0}
    },

    Transform = {
        Position = {0,500,0},
        Scale = {1,1,1},
        Rotation = {0,0,0}
    },

    Rigidbody = {
        Type = "Hull",
        Mass = 1
    },

    Prueba = {
        valor1 = 1,
        valor2 = 3,
        valor3 = "Quack"
    }
}

entidad2 = {
    Components = {"MeshRenderer"},

    MeshRenderer = {
        Mesh = "Sphere",
        Position = {0,50,0},
        Material = "GameExample/beti"
    },
}