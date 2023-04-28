# Robothon-2023-Grand-Challenge-TechWi(e)nBot-Team-Report

This page deals with the main-task (Taskboard). To see the report of the [BYOD](BYOD.md)-report, click here.

<h2>Hardware Setup</h2>

The setup consists of
![Setup](https://user-images.githubusercontent.com/131485125/234953688-bdba439e-ceb5-40f2-8fe3-e05b4a331f83.png)

<ul>
  <li>Base (Table consists of aluminum profiles)</li>
  <li>ABB CRB 1100 + OmnicorC30 control unit </li>
  <li>Schunk parallel gripper (MPC 075) with 3d printed plates</li>
  <li>COGNEX 821-10160-1R camera</li>
  <li>turning-table as additional axis (self-crafted)</li>
  <li>additional tools in order to fullfill the tasks</li>
</ul>

<h2>General Approach</h2>
Our goal was to successfully complete all of the tasks with perfection. However, our robot's range was not sufficient to solve the task from any given orientation of the taskboard. To overcome this limitation, we decided to create tools, such as a gear-feather mechanism to open the door, and an additional axis to rotate the whole taskboard to a suitable orientation. The additional axis is controlled by the robot control system and does not require any human interaction. While there are specific orientations of the taskboard in which the additional tools are not necessary, we wanted to ensure that our robot could adapt to any random orientation of the taskboard.

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/234349474-f773ca18-ef78-40f8-976f-d72834209baf.JPG" width="300" height="300"flex: 1;">
  <img src="https://user-images.githubusercontent.com/131485125/234816714-c291a85c-1240-44d8-a683-d1dffe322b09.JPG" width="350" height="300" alt="Image 2" style="flex: 1;">
  <img src="https://user-images.githubusercontent.com/131485125/234817050-e7402eee-5f0f-4e81-a629-87531723a0b1.JPG" width="350" height="300" alt="Image 2" style="flex: 1;">
</div>


Despite the tools we presented, the gripping mechanism itself was the most crucial part of our design. To perform all of the requested tasks efficiently, we needed to create a gripper plate that was significantly different from any existing types on the market. Our solution, especially for the wire-winding task, was to incorporate pulleys into the plates. These pulleys, when in a closed configuration, created a small gap for the wire, allowing it to be held tightly while still maintaining the necessary freedom of motion to wind the wire.


<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/234351693-f515091a-93aa-4f87-b97f-a567f6041716.jpg" width="400" height="300")>
  <img src="https://user-images.githubusercontent.com/131485125/234648049-21f379e8-f861-4e4b-a01f-ac92bf939d04.JPG" width="300" height="300")>
</div>





<h2>Software solution</h2>


<h3>Methods</h3>

Our approach was to split all of the sub-tasks into separate methods to make them independent of any given sequence. However, there is an initialization sequence that was provided by the task.

![flowchart](https://user-images.githubusercontent.com/131485125/234347707-d8d07b28-8fe2-4b5c-8b70-358c335a7c51.png)

In the flowchart above, you can see that the process 'camera action' is repeated three times. This indicates that a specific camera job is loaded onto the camera, executed, and the results are received. More information about the camera (vision) jobs will be provided in the next paragraphs.

<h3>Vision System: Board localisation</h3>
We used the Cognex Vision framework in order to locate the taskboard and its orientation. In detail, we generated several different "jobs", which got called by ABB's rapid-code.

<ul>
  <li>"newTaskboard.job" -> result: position and orientation of the taskboard</li>
  <li>"TaskboardOnTable.job" ->result: position and orientation of the taskboard </li> 
  <li>"BYOD.job" ->result: position and orientation of the BYOD</li>
</ul>



In simple terms, the Cognex software generates an additional coordinate system that refers to the origin of the calibration coordinate system. To use the coordinate system of the taskboard, the object frame is copied from the camera target to a coordinate system that is available in ABB's RobotStudio IDE.




![PatternRecognitionTaskboard](https://user-images.githubusercontent.com/131485125/234950507-a29cda0c-0c72-4bd2-b987-41a73b3fd554.png)
 
 The origin of the taskboard coordinate system is set to the upper left corner (indicated by the green symbol), and all other positions are "hardcoded" with respect to this point.




<h3>Vision System: Slider adjustment</h3>
Seperated from the localisation of the taskboard, there is another camera job to execute 
<ul>
<li>"SliderDisplay.job" ->result: distance beetween green and yellow triangle</li>
</ul>


In order to detect the triangles, we used what are called 'blobs.' Blobs are a collection of several pixels with a common brightness. Since the blue screen of the display has a different brightness and number of pixels than the triangles, it is possible to separate them.

Since the orientation and position are already known by the system, the only important information is the distance between the triangles. Unfortunately, there are several edge cases that need to be considered:

| Case    | definition                                                                                                                   |     Image    | sequence                                                      |
|---------|------------------------------------------------------------------------------------------------------------------------------|:------------:|---------------------------------------------------------------|
| regular | camera can distinguish between both triangles and reed the distance beetween them correctly                                  | ![TriangleDistanceMarked](https://user-images.githubusercontent.com/131485125/234574520-8d1e028a-296e-49c9-9d5b-1acc3d5d9e94.png) | robot moves slider to determined position                     |
| overlap | triangles overlap. So the blob algorythm can´t find 2 seperate triangles, since they merged to  one big collection of pixels |![TriangleOverlap](https://user-images.githubusercontent.com/131485125/234843506-c9a3f061-fc72-403f-bd1b-bd166612e150.png)| robot moves slider 5mm from middle postion in both directions |
| done    | A rare case, in which the triangles overlap so tight, that the task is already done by simply moving to the middle triangle. | ![TriangleGone](https://user-images.githubusercontent.com/131485125/234945193-eb437715-8e58-4710-8580-3896ff1e91fa.png)| should be none. To avoid errors due to false interpretation, we decided to start the same sequence like in "overlap".                                                           |


<h2>Repository of software modules</h2>
The created software solution is based on third parties software:

<ul>
  <li>ABB robot studio IDE, usage of software package Rapid</li>
  <li>Cognex Vision framework </li> 
  <li>Arduino IDE + stepper.h library (stepper motor for turning table)</li>
</ul>

<h2>How to run</h2>How to run
To run the software solution, follow this sequence:
<ul>
  <li>Install ABB Robot Studio or run directly from FlexPendant via USB</li>
  <li>Import SoftwareSolutionRobot</li> 
  <li>Connect the camera to the controller via Profinet</li>
  <li>Store all .job files on the camera</li>
  <li>calibrate the camera via cognex grid</li>
  <li>run the solution via ABBs IDE</li>
</ul>

<h2>Authors</h2>
(in alphabetical order)


[Sebastian Neuhofer](https://www.linkedin.com/in/sebneuhofer/), [Christian Scheidl](https://www.linkedin.com/in/christian-scheidl-793658252/), [David Seyser](https://www.linkedin.com/in/david-seyser/), [Julian Smole](https://www.linkedin.com/in/julian-smole-9b7537121/)



