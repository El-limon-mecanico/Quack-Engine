﻿scene1 = {
    entities = {"entidad1"}
}

entidad1 = {
    Components = {"Transform", "MeshRenderer","Rigidbody", "Prueba"},

    Transform = {
        Position = {0,500,0},
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
        Position = {50,500,0},
        Scale = {1,1,1},
        Rotation = {0,0,0}
    },

    MeshRenderer = {
        Mesh = "Sphere",
        Position = {50,500,0}
    },

    Rigidbody = {
        Type = "Sphere",
        Mass = 1
    }   
}