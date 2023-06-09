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

![FlowchartBYOD_V2](https://user-images.githubusercontent.com/131485125/235315715-ccb48426-f2be-454d-a57b-fcd384422d6b.png)


<h3>Vision System</h3>
Similar to the main task, the position and orientation of the device must be determained. Therefore wie applied a similar alogrythm to detect all information needed.

<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/235079110-68e7f3d0-95ec-42c0-939a-35da4e4338ef.png" width="700" height="400")>
</div>

The origin of the new target coordinate system is set to the bottom left corner and all other targets reffer to this origin.

<h2>Difficulties</h2>

Since we wanted to utilize as many wire interactions as possible, we created a task that presented some difficulties during operation. One of the biggest challenges was the usage of two different wires. While executing the task, we had to ensure that both wires did not interfere with each other and impede their performance. We developed a well-prepared code sequence to solve this issue, which has been successful in practice. In an iterative process, we developed strategies to cope with the unpredictable behaviour of the wires as well as possible.

Another problem arose due to the small movements of the device. Since the device is not mounted to the table and our table is not well balanced, fast movements from the robot can lead to small changes in the position and orientation of the device during execution. To bypass this problem, we call the method 'camera action' several times during execution. Thus, the position and orientation of the device remains up-to-date. The only compromise we had to make is that execution time will increase since every 'camera action' call needs up to 2 seconds of additional execution time.
