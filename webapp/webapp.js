import { io } from 'socket.io-client';



socket=io.connect('/webapp');

socket.on("connect",(connect)=>{
    console.log("connected")
	mySocket.emit("LIGHT") 
    var ledstt = [1,1,1];
    var btn = document.getElementById('btn');
    btn.onclick = () => {
        var json = {
            led : ledstt,
        }
        socket.emit('LED',json);
    }
    socket.on('LIGHT',(LIGHT)=>{
        var lg = document.getElementById('lg');
        lg.innerHTML = (LIGHT.digital ==1) ? 'Sensor không bắt được ánh sáng' : ' Sensor bắt được ánh sáng';
    })
    


})