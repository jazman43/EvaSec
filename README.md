# EvaSec
a basic home camera security system
----
This is mostly a learning project that i felt like i needed to create. 
I just so happen to have an old laptop perfect to host this on. And sadly
there had been a few burglaries in my area. these 3 things inspried me to 
create this :)

---
## current features
- gets up to 1 cameras attached to divice. 
- records and stores in folder 'recordings/Camera_num' 
- records 10 min video's before creating a new file. 

files : camera / date d-m-y time h-m-s / .mp4
        Cam_num_Time_25-03-25_13-23-45.mp4

--- 
## Planed features
- object tracking with notifications this should send a message with a image of object that set it off with time date and camera id
- local host web portal with setting config, live stream of cameras.
  
---
### Project Pram/ Third party

- openCV
- c++ 17
- CMake
- Linux