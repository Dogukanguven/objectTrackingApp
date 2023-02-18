# Object Tracking Application

## Tracking algorithms

#### 1- MEDIANFLOW
#### 2- BOOSTING
#### 3- MOSSE
#### 4- CSRT
#### 5- TLD
#### 6- KCF

## Compiling and running the application
```bash
git clone https://github.com/Dogukanguven/objectTrackingApp.git
cd objectTrackingApp
mkdir build && cd build
cmake ..
make
./TrackingApp -v ../testData/test1.mp4 -t CSRT
```

## Result
![Result gif](/result/result.gif "Result")