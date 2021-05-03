scene1 = {
    entities = {"entidad1","entidad2"}
}

entidad1 = {
    Components = {"Transform", "MeshRenderer", "Rigidbody", "Prueba"},

    Transform = {
        Position = {0,5,0},
        Scale = {1,1,1},
        Rotation = {0,0,0}
    },

    MeshRenderer = {
        Mesh = "Suzanne.mesh",
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
    Components = {"Transform", "MeshRenderer", "Rigidbody"},

    Transform = {
        Position = {0,-3,0},
        Scale = {5,5,1},
        Rotation = {-90,0,0}
    },

    MeshRenderer = {
        Mesh = "Plane",
    },

    Rigidbody = {
        Type = "Cube",
        Mass = 0
    }   
}