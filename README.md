# Robothon-2023-Grand-Challenge-TechWi(e)nBot-Team-Report

This page deals with the main-task (Taskboard). To see the report of the [BYOD](BYOD.md)-report, click here.

<h2>Hardware Setup</h2>

The setup consists of

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/234953688-bdba439e-ceb5-40f2-8fe3-e05b4a331f83.png" width="450" height="500")>
</div>


<ul>
  <li>Base (Table consists of aluminum profiles)</li>
  <li>ABB CRB 1100 + OmnicorC30 control unit </li>
  <li>Schunk parallel gripper (MPC 075) with 3d printed plates</li>
  <li>COGNEX 821-10160-1R camera</li>
  <li>(optional) turning-table as additional axis (self-crafted)</li>
  <li>additional tools in order to fullfill the tasks</li>
</ul>

<h2>General Approach</h2>
Our goal was to successfully complete all of the tasks with perfection. However, our robot's range is not sufficient to solve the task from any given orientation of the taskboard without constraints. 

[constraints](README.md#constraints-due-to-setup), or see below

To overcome this limitation, we decided to create tools, such as a gear-spring mechanism to open the door, and an additional axis to rotate the whole taskboard to a suitable orientation. The additional axis is controlled by the robot control system and does not require any human interaction. While there are specific orientations of the taskboard in which the additional tools are not necessary, we wanted to ensure that our robot could adapt to any random orientation of the taskboard. However, at the time of submission the integration of the turningtable to the robot system does not work with a sufficient reliability. Thus, we did not use it in our final submission video. Nevertheless we made a great effort in the developing process, which is why we still want to present it in our report.

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/234349474-f773ca18-ef78-40f8-976f-d72834209baf.JPG" width="300" height="300"flex: 1;">
  <img src="https://user-images.githubusercontent.com/131485125/234816714-c291a85c-1240-44d8-a683-d1dffe322b09.JPG" width="350" height="300" alt="Image 2" style="flex: 1;">
  <img src="https://user-images.githubusercontent.com/131485125/234817050-e7402eee-5f0f-4e81-a629-87531723a0b1.JPG" width="350" height="300" alt="Image 3" style="flex: 1;">
</div>


Despite the tools we presented, the gripping mechanism itself was the most crucial part of our design. To perform all of the requested tasks efficiently, we needed to create a gripper plate that was significantly different from any existing types on the market. Our solution, especially for the wire-winding task, was to incorporate pulleys into the plates. These pulleys, when in a closed configuration, created a small gap for the wire, allowing it to be held tightly while still maintaining the necessary freedom of motion to wind the wire.


<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/234351693-f515091a-93aa-4f87-b97f-a567f6041716.jpg" width="400" height="300")>
  <img src="https://user-images.githubusercontent.com/131485125/234648049-21f379e8-f861-4e4b-a01f-ac92bf939d04.JPG" width="300" height="300")>
</div>
                                                                                                                                            

<u> Why do we use such a complex construction for the wire-gripper part?:</u>
                                                                                                                                            
  The reason why we decided to use pulleys is that from our point of view it is the method which damages the wire least. Other options - like simply grabbing it or using a bigger gap which allows some motion - would still evoke very high friction and would destroy the wire over time. With our solution, friction is neglectable and as a matter of fact the service life of the wires increases.                                                                                                                                          
                                                                                                                                            





<h2>Software solution</h2>


<h3>Methods</h3>

Our approach was to split all of the sub-tasks into separate methods to make them independent of any given sequence. However, there is an initialization sequence that was provided by the task.

![flowchart](https://user-images.githubusercontent.com/131485125/234347707-d8d07b28-8fe2-4b5c-8b70-358c335a7c51.png)

In the flowchart above, you can see that the process 'camera action' is repeated three times. This indicates that a specific camera job is loaded onto the camera, executed, and the results are received. More information about the camera (vision) jobs will be provided in the next paragraphs.

<h3>Vision System: Board localisation</h3>
We used the Cognex Vision framework in order to locate the taskboard and its orientation. In detail, we generated several different "jobs", which got called by ABB's rapid-code. Specifically, we used the Cognex PatMax RedLine Pattern algorithm.


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
| overlap | triangles overlap. So the blob algorythm can´t find 2 seperate triangles, since they merged to  one big collection of pixels |![TriangleOverlap](https://user-images.githubusercontent.com/131485125/234843506-c9a3f061-fc72-403f-bd1b-bd166612e150.png)| robot moves slider 5mm from middle postion in both directions. This sequence is indicated by a short blue blink of the robot´s built-in lamp |
| done    | A rare case, in which the triangles overlap so tight, that the task is already done by simply moving to the middle triangle. | ![TriangleGone](https://user-images.githubusercontent.com/131485125/234945193-eb437715-8e58-4710-8580-3896ff1e91fa.png)| should be none. To avoid errors due to false interpretation, we decided to start the same sequence like in "overlap".                                                           |



<h2>Constraints due to Setup</h2>
Since we use only one robot to solve the task (asumption that turning table is not implemented to the solution yet), there are some constraints which have to be considered while placing the taskboard to a specific position/orientation 

<h3>camera frame</h3>
First of all, the area of positionining is constrainted by the field which is covered by the camera. Due to the chosen height of the camera and its technical properties, we are able to locate the taskboard in a area which looks like this:

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/235298559-5d8cb600-b69f-45ec-a1b2-6e238f7cf07d.png" width="500" height="300")>
</div>




<h3>Range of robot</h3>
Second topic to consider is the range of motion of the ABB CRB 1100. In general the range of the TCP0 (center of flange) is about 74cm. In addition, to solve the given tasks, the range of "free positioning" decreases. In particular, the taskboard must be placed in an orientation, so that the "wind wire" area faces the robot´s base. With our tools and configuration, it is not possible to rotate the taskboard so that the winding area is orientated away from the base.


<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/235298559-5d8cb600-b69f-45ec-a1b2-6e238f7cf07d.png" width="300" height="180")>
  <img src="https://user-images.githubusercontent.com/131485125/235298764-fb47aa3f-06b9-4b0c-b5da-6b162d7c062c.png" width="300" height="180")>
</div>

Another aspect to consider is that the taskboard must maintain a minimum distance from the robot's base. If this minimum is undercut, the robot's joints would collide, and the robot would stop. While holding this minimum distance, it is nearly impossible to open the door by simply grabbing the knob and performing a circular movement that is out of the robot's reach. Hence, opening the door and winding the wire would be mutually exclusive. Therefore, we created the 'door-opener' tool, which bypasses the problem of limited range. With this tool, we are now able to open the door from the front side.



<h3>placing probe in temporarily clamp</h3>
Due to the fact that we only use one robot, the combination of the winding task and the probe itself cause another constraint. After pluging the probe into the regular clamp, we can not plug it back to the white socket because it would interfere with the winding task. So we have to plug it to an temporarily clamp which allows us to taking it back from a determained position after the winding task. Since we must wind the wire 2 times to guarantee an "always-working solution", the rest of the wire becomes very short. That is the reason why we were forced to reduce the accepted orientation-angle to about -10° (left image) to 45° (right image). To clarify: orienting the long side of the taskboard parallel to the robot´s base would lead to an angle of 0°. Angle is counted positive counter-clockwise.

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/235300522-30daf56c-9985-4c78-ad17-7fd9d1f6a211.png" width="300" height="180")>
  <img src="https://user-images.githubusercontent.com/131485125/235302042-2fe8b154-f8a5-42e7-9763-b3a0ff893d73.png" width="300" height="180")>
</div>




If we fall below the bottom limit (left image), the wire will be too short and would tear the probe from the temporarily clamp. If we exceed the the angle in positiv direction (right image), the winding task won`t work due to the limited range of motion of the robot.

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/235300593-be556ba0-e33a-40fe-b122-9ca1f2bf7369.png" width="300" height="180")>
  <img src="https://user-images.githubusercontent.com/131485125/235301030-cbb0a773-c326-4454-a24d-6f992da2bf5b.png" width="350" height="180")>
</div>
                                                                                                                                            
<h2>Turntable</h2>
To reduce the amount of constraints we have in our system, we decided to build a turntable on which we mount the taskboard. The turntable is driven by a stepper motor, with a spur gear mounted on it to transfer the torgue from the motor to the internal spur gear, which acts as the table-top where the taskboard is located.
                                                                                                                                       
<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/234816714-c291a85c-1240-44d8-a683-d1dffe322b09.JPG" width="350" height="300" alt="Image 2" style="flex: 1;">                                                                                                                   
</div> 
                                                                                                                                              
The turntable is programmed and wired to an arudino uno, to control the stepper motor we used the Stepper.h library, therefor we only need to provied an angular value to start the turning process, this would mean that we would need a ethernet or TCP/IP connection from ABBs control unit to our arduino, but in the timespan of this project we werent able to achive such a connection and therefor had to circumvent that problem of sending and receiving data from and to the arduino. We resolved this problemby simply sending a digital output signal from the control unit, for a specified period of time, depending on the angular value we received form our camera. In the arduino program we could then create a while-loop, which is only active as long as we receive the signal from the controller, in which we send a turn-signal to the stepper motor. This way we were able to create a functioning turntable which can reposition us every run. In addition, we have decided to build brakes that engage with the internal spur gear with a rack when the table is stationary. This is because the motor we decided to use has a small holding-torque and could lead to the robot turning the whole mechanism at some tasks. These breaks are also controlled via the arduino.

                                                                                                                                       
<div style="display: flex;">
 <img src = "https://user-images.githubusercontent.com/96821053/235343906-97bb3e26-f84d-4dc1-97f0-368276d82e4e.png" width="600" height = "360">                                                                                                                                           
</div>                                                                                                                                            
                                                                                                                                          

<h2>New insights</h2>
In general, participation in the robothon challenge was a great pleasure - although it was extremly time-consuming. To give a short conclusion, we want to list our most important new insights in the developing-process of new robotic-solutions:


<ul>
  <li>if the task seems to be impossible: be creative and create a tool to solve it</li>
  <li>first things first: Set up the working station perfectly at the beginning, not in the end. (we had to learn it the hard way) </li>
   <li>mount camera seperatly from the robot. If robot moves fast, the camera wiggles a bit</li>
  <li>wires are hard to control and their behaviour is nearly unpredictable</li> 
  <li>wire´s behaviour change tremendously after changing the velocity of the robot</li>
  <li>clean up your working station before using the robot -> it will definitely reduce damages</li>
  <li>treat any suggestion for a solution instead of ruling it out instantly </li>
 
</ul>


<h2>How to run</h2>

To run the software solution, follow this sequence:
<ul>
  <li>Print all .step files with a 3d printer (slice to gcode)</li>
  <li>Mount gripper</li>
  <li>Install ABB Robot Studio or run directly from FlexPendant via USB</li>
  <li>Import the software solution  </li>  
  
  [SoftwareSolutionRobot](./SoftwareSolutionRobot.zip)
  
  <li>Connect the camera to the controller via Profinet</li>
  <li>Select camera IP adress in the IDE</li>
  <li>Store all .job files on the camera</li>
  
  [CamJobs](./CamJobs.zip)
  
  <li>change light level to fit to the environment</li>
  <li>calibrate the camera via cognex grid</li>
  <li>calibrate robots workobject coordinate system to the grid</li>
  <li>run the solution via ABBs IDE in hand-operation-mode and check if all trajectories are suitable</li>
  <li>change robots settings to automatic mode in order to operate with full speed</li>
</ul>

<h2>Repository of software modules</h2>
The created software solution is based on third parties software:

<ul>
  <li>ABB robot studio IDE, usage of software package Rapid</li>
  <li>Cognex Vision framework </li> 
  <li>Arduino IDE + stepper.h library (stepper motor for turning table)</li>
</ul>




<h2>Authors</h2>
(in alphabetical order)


[Sebastian Neuhofer](https://www.linkedin.com/in/sebneuhofer/), [Christian Scheidl](https://www.linkedin.com/in/christian-scheidl-793658252/), [David Seyser](https://www.linkedin.com/in/david-seyser/), [Julian Smole](https://www.linkedin.com/in/julian-smole-9b7537121/)



