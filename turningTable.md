<h2>Turntable</h2>
To reduce the amount of constraints we have in our system, we decided to build a turntable on which we mount the taskboard. The turntable is driven by a stepper motor, with a spur gear mounted on it to transfer the torgue from the motor to the internal spur gear, which acts as the table-top where the taskboard is located.
                                                                                                                                       
<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/131485125/234816714-c291a85c-1240-44d8-a683-d1dffe322b09.JPG" width="350" height="300" alt="Image 2" style="flex: 1;"> 
  <img src="https://user-images.githubusercontent.com/131485125/234817050-e7402eee-5f0f-4e81-a629-87531723a0b1.JPG" width="350" height="300" alt="Image 3" style="flex: 1;">
</div> 
<h3> Motor control </h3>                                                                                                                                              
The turntable is programmed and wired to an arudino uno, to control the stepper motor we used the Stepper.h library, therefore we only need to provied an 
angular value to start the turning process, this would mean that we would need a ethernet or TCP/IP connection from ABBs control unit to our arduino, 
but in the timespan of this project we were not able to achive such a connection and therefor had to circumvent that problem of sending and receiving data 
from and to the arduino. We resolved this problemby simply sending a digital output signal from the control unit, for a specified period of time, depending 
on the angular value we received from the camera. In the arduino program we could then create a while-loop, which is only active as long as we receive the signal 
from the controler, in which we send a turn-signal to the stepper motor. This way we were able to create a functioning turntable which can reposition the taskboard every run.

<h3>Break Mechanism </h3>
In addition, we decided to build brakes that engage with the internal spur gear with a rack when the table is stationary. This is because the stepper motor use has 
a small holding-torque and could lead to the robot turning the whole mechanism at some tasks. These breaks are also controlled via the arduino.

                                                                                                                                       
<div style="display: flex;">
 <img src = "https://user-images.githubusercontent.com/96821053/235343906-97bb3e26-f84d-4dc1-97f0-368276d82e4e.png" width="600" height = "360">                                                                                                                                           
</div>     

<h3>Integration of the turntable to the system</h3>
At the time of submission, the turntable has not been integrated into the system due to some difficulties that need to be addressed. The main issue is that the turntable's height increases the likelihood of configuration errors for the robot. To resolve this, we suggest embedding the turntable into the working table. Another consideration is that the camera would need to be recalibrated for the new setting, which would require additional time.

In summary, we have proposed a simple 'one-axis' solution to overcome the constraints of orientation. This approach demonstrates the redundancy of a second robot and provides a more cost-effective solution.


