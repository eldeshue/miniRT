## **miniRT**

## **Introduction**

Simple 3D-object renderer based on Raytracing.

## **Installation**

### **For Mac**
1. Clone the repository:
```
git clone https://github.com/eldeshue/miniRT.git
```
2. Navigate to the project directory:
```
cd miniRT
```
3. Build the project:
```
make all
```
4. Start the project:
```
./miniRT {scene description file}
```

### **For Linux**
to run this project on Linux, you need X11 library.
1. Clone the repository:
```
git clone https://github.com/eldeshue/miniRT.git
```
2. Navigate to the project directory:
```
cd miniRT
```
3. Change branch:
```
  git switch 49-feat-minirt-for-linux
```
4. Build the project:
```
make all
```
5. Start the project:
```
./miniRT {scene description file}
```


## **Usage**

### **Defining Scene**
To run miniRT, user need to describe a scene to render. miniRT take as a first argument a scene description file with the .rt extension. 

all direction vector's(camera's view, plane normal, cylinder, ... ) must be normalized.

1. Camera
```
C {position x},{position y},{position z} {viewing direction vector x},{viewing direction vector y},{viewing direction vector z} {hFOV, degree}
```

2. Ambient Light
```
A {Intensity, 0.0~1.0} {color, R, 0~255},{color, G, 0~255},{color, B, 0~255}
```

3. Light Source
```
L {position x},{position y},{position z} {Intensity, 0.0~1.0} {color, R, 0~255},{color, G, 0~255},{color, B, 0~255}
```

4. Plane Object
```
pl {position x},{position y},{position z} {normal vector x},{normal vector y},{normal vector z} {color, R, 0~255},{color, G, 0~255},{color, B, 0~255}
```

5. Sphere Object
```
sp {center position x},{center position y},{center position z} {diameter} {color, R, 0~255},{color, G, 0~255},{color, B, 0~255}
```

6. Cylinder Object
```
cy  {center position x},{center position y},{center position z} {direction vector x},{direction vector y},{direction vector z} {diameter} {height} {color, R, 0~255},{color, G, 0~255},{color, B, 0~255}
```

7. Cone Object
```
co  {plane center position x},{plane center position y},{plane center position z}  {tip position x},{tip position y},{tip position z} {color, R, 0~255},{color, G, 0~255},{color, B, 0~255}
```

For further information, please refer to the files in the scene directory.

### **Run**
```
./miniRT {scene description file}
```

## **Authors and Acknowledgment**

miniRT was created by **[eldeshue](https://github.com/eldeshue)** and **[HyWChoi](https://github.com/HyWChoi)**.

## **Contact**

If you have any questions or comments about miniRT, please contact **[eldeshue](mailto:eldeshue@naver.com)**.
