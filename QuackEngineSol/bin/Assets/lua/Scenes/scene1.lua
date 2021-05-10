scene1 = {
    entities = {"defaultCamera","entidad1", "entidad2", "sceneLight"}
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
        Mass = 1,
        Trigger = false,
        Static = false
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
        Mass = 1,
        Trigger = false,
        Static = true
    }   
}

defaultCamera = {
    Components = {"Transform", "Camera", "Prueba"},

    Transform = {
        Position = {10,10,10},
        Scale = {1,1,1},
        Rotation = {0,0,0}
    },

    Camera = {
        Name = "MainCam",
        Background = {1,1,0},
        LookAt = {0,0,0},
        Width = 0,
        Height = 0,
        NearClipDistance = 1,
        FarClipDistance = 100000,
        ProjectionType = "Perspective"
    },

    Prueba = {
        valor1 = 1,
        valor2 = 3,
        valor3 = "Quack"
    }
}

sceneLight = {
    Components = {"Transform", "Light"},

    Transform = {
        Position = {10,10,10},
        Scale = {1,1,1},
        Rotation = {0,0,0}
    },

    Light = {
        LightType = 1,
        DiffuseColor = {1,1,1},
        SpecularColor = {1,1,1},
        Direction = {0,0,0},
        PowerLevel = 1,
        InnerAngle = 30,
        OuterAngle = 90,
        isOn = true
    }
}