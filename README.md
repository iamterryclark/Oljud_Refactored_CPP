#Oljud {Noise}

An Interactive Audio Visual Tool for artists. Linking Kinect to Ableton and mapping movements to music.

##How to Run
- Windows Operating system only Visual Studio 2015
- Put this folder under you openFrameworks myApps Folder
- Download ofKinectForWindows2 Library by Elliott Woods - https://github.com/elliotwoods/ofxKinectForWindows2
- Install KinectV2 SDK from Windows - https://www.microsoft.com/en-gb/download/details.aspx?id=44561 (run the examples in this program to test the Kinect works)
- Run the app.
- If you want to send OSC you should make sure you IP address and port number are correct for the application you are running.

##Current Status
I have refactored most of the code from my original project so this code can be marked based on code readability, techniques I have used etc.

The app runs well and utilises memory management to produce the particles. I managed to implement 5 classes, with include skeleton tracking, gestures (which I created last year) and a particle system, with noise. I seem to get the correct values from the Kinect right up until gestures as this needs more work in order to calibrate the gestures better. However, I would like to implement Euclidean distance here in order to create more interesting gestures.
