document.addEventListener("DOMContentLoaded", () => {
  const websocket = new WebSocket("ws://localhost:8766");
  
  websocket.onopen = () => console.log("Conectado al servidor WebSocket SwitchFoco");
  var focoImg = document.getElementById("focoImg");

  var focoImages = {
    foco_on: "./img/foco_on.png",
    foco_off: "./img/foco_off.png",
  };

  var theme = document.getElementById('theme-css');
  var light =document.getElementById("cont-light");
  var graphic=document.getElementById("cont-graphic");


  
  // Manejar mensajes recibidos del servidor
  websocket.onmessage = (event) => {
    const message = event.data;
    console.log("Mensaje recibido:", message);
    
    // Actualiza la interfaz de usuario según el estado del LED
    const toggleBtn = document.getElementById("toggleBtn");

    if(message === "1") {
      toggleBtn.checked = true;
      focoImg.src=focoImages.foco_on
      theme.href = "index.css";
      light.classList.add('bg-white');
      graphic.classList.add('bg-white');
      light.classList.remove('bg-gray-700');
      graphic.classList.remove('bg-gray-800');

    } else if(message === "0") {
      toggleBtn.checked = false;
      focoImg.src=focoImages.foco_off
      theme.href = "./dark-theme.css"; // Cambia tema oscuro
      light.classList.remove('bg-white');
      graphic.classList.remove('bg-white');
      light.classList.add('bg-gray-700');
      graphic.classList.add('bg-gray-800');
    }
  };

  document.getElementById("toggleBtn").addEventListener("change", function () {
    const command = this.checked ? "1" : "0";
    websocket.send(command);
    console.log("Enviado:", command);
  });
});
