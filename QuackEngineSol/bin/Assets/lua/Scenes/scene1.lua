scene1 = {
    entities = {"entidad1"}
}

entidad1 = {
    Components = {"Transform", "MeshRenderer", "Prueba"},

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

camera = {
    Components = {"Transform", "Camera"}

    Transform = {
        Position = {1000,1000,1000},
        Scale = {1,1,1},
        Rotation = {0,0,0}
    }

    Camera = {
        Name = "MainCam",
        Background = {1,1,0},
        LookAt = {0,0,0}
    }
}