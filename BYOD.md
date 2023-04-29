This page deals with the BYOD-Task. To see the report of the [Taskboard](README.md)-report, click here.
# BYOD: verification of a voltage supply unit

The selected device for the BYOD task is an old voltage supply unit that has been used in a laboratory. Since these devices require regular verification, an automated solution would decrease the workload for workers in the lab and enhance the service life of the devices by reducing unnecessary exchanges.

<h2>Setup</h2>
There are many targets which have to be used in order to fullfill the task. The most important targets are highlighted in the following image

![SetupBYOD](https://user-images.githubusercontent.com/131485125/235075878-e2d5c995-f002-4cae-9e4e-9c7058512399.png)

We used the same gripper like in the main-task.

<h2>Software solution</h2>


<h3>Methods</h3>
Our approach was to split all the sub-Tasks into seperate "methods", in order to be independent to any given sequence. Of course, there is an init-Sequence which has a "logical" order. You can see the methods in the following flowchart diagram.

![image](https://user-images.githubusercontent.com/131485125/235076912-af4cfbf6-cb72-4c1f-9a8e-bc3d1cda2b36.png)

<h3>Vision System</h3>
Similar to the main task, the position and orientation of the device must be determained. Therefore wie applied a similar alogrythm to detect all information needed.

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/235079110-68e7f3d0-95ec-42c0-939a-35da4e4338ef.png" width="700" height="400")>
</div>

The origin of the new target coordinate system is set to the bottom left corner and all other targets reffer to this origin.


