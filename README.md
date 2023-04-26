# Robothon-2023-Grand-Challenge-TechWi(e)nBot-Team-Report

<h2>Hardware Setup</h2>

The setup consists of

<ul>
  <li>Base</li>
  <li>ABB CRB 1100 </li>
  <li>Schunk parallel gripper with 3d printed plates</li>
  <li>turning-table as additional axis (self-crafted)</li>
  <li>additional tools in order to fullfill the tasks</li>
</ul>

<h2>General Approach</h2>
Our goal was to succeed in all of the tasks with perfection. Since our robot´s range was not big enough to solve the task from any given orientation of the taskboard, we decided to create tools (e.g. a gear-feather-mechanism to open the door) and an additional axis in order to rotate the whole taskboard in an orientation which is suitable for the task. Of course, the additional axis is controlled by the robot-control-system and does not need any human interaction.

<figure>
  <img src="https://user-images.githubusercontent.com/131485125/234349474-f773ca18-ef78-40f8-976f-d72834209baf.JPG" width="300" height="300">
</figure>

Despite the presented tools, of course the gripping mechanism itself is the most important design part. In order to solve all requested task in a very sufficient way, we had to find a gripper-plate which is very different to all allready known types on market. Our solution - especially to cope with the wire-winding task is to include pulleys into the plates. Those pulleys - in closed configuration - form a small gap for the wire in order to hold it tight, but still keep the requiered freedom of motion to wind the wire.



<figure>
  <img src="https://user-images.githubusercontent.com/131485125/234351693-f515091a-93aa-4f87-b97f-a567f6041716.jpg" width="400" height="300")>
</figure>



<h2>Software solution</h2>


<h3>Methods</h3>

Our approach was to split all the sub-Tasks into seperate "methods", in order to be independent to any given sequence. Of course, there is an init-Sequence which was given by the task.

![flowchart](https://user-images.githubusercontent.com/131485125/234347707-d8d07b28-8fe2-4b5c-8b70-358c335a7c51.png)

<h3>Vision System: Board localisation</h3>
We used the Cognex Vision framework in order to locate the taskboard and its orientation. In detail, we generated several different "jobs", which got called by ABB's rapid-code.

<ul>
  <li>"newTaskboard.job" -> result: position and orientation of the taskboard</li>
  <li>"TaskboardOnTable.job" ->result: position and orientation of the taskboard </li> 
  <li>"BYOD.job" ->result: position and orientation of the BYOD</li>
</ul>

Simply speaking, the cognex software generates an additional coordinate-system which refers to the origin of the calibration-coordinate system. In order to use the coordinate system of the taskboard, the object-frame is coppied from the camera target to coordinate-system which is available in ABB´s robot studio IDE

insert image!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



<h3>Vision System: Slider adjustment</h3>
Seperated from the localisation of the taskboard, there is another camera job to execute 
<li>"Slider.job" ->result: distance beetween green and yellow triangle</li>

In order to detect the triangles, we used so called "blobs". Blobs are a collection of several pixels with a common brightness. Since the blue screen of the display has an other brightnes and amount of pixels than the triangles, it is possible to seperate them.

Since orientation and position are already known by the system, the only important information is the distance between the triangles. Unfortunately, there are several edge cases to cope wiht:

| Case    | definition                                                                                                                   |     Image    | sequence                                                      |
|---------|------------------------------------------------------------------------------------------------------------------------------|:------------:|---------------------------------------------------------------|
| regular | camera can distinguish between both triangles and reed the distance beetween them correctly                                  | insert Image | robot moves slider to determined position                     |
| overlap | triangles overlap. So the blob algorythm can´t find 2 seperate triangles, since they merged to  one big collection of pixels | ![TriangleDistanceMarked](https://user-images.githubusercontent.com/131485125/234574520-8d1e028a-296e-49c9-9d5b-1acc3d5d9e94.png) | robot moves slider 5mm from middle postion in both directions |
| done    | A rare case, in which the triangles overlap so tight, that the task is already done by simply moving to the middle triangle. | insert Image | none                                                          |


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
  <li>Install ABB Robot Studio</li>
  <li>Import SoftwareSolutionRobot</li> 
  <li>Connect the cammera to the controller via Profinet</li>
  <li>Store all .job files on the camera</li>
  <li>calibrate the camera via cognex grid</li>
  <li>run the solution via ABBs IDE</li>
</ul>

<h2>Authors</h2>
(in alphabetic order)


[Sebastian Neuhofer](https://www.linkedin.com/in/sebneuhofer/), [Christian Scheidl](https://www.linkedin.com/in/christian-scheidl-793658252/), [David Seyser](https://www.linkedin.com/in/david-seyser/), [Julian Smole](https://www.linkedin.com/in/julian-smole-9b7537121/)

 


