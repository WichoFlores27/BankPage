console.log("Magic!");
let message;
message = 'Hello World!';
console.log(message);
function changeText() {
    let heading = document.querySelector('h1');
    heading.textContent = ':0';
}
function saludar() {
    let nombre = document.getElementById('nameInput').value;
    let saludotext = document.getElementById('saludo');

    if (nombre) {
        saludotext.textContent = 'Hola, ' + nombre + '!';
    } else {
        saludotext.textContent = 'Hola, Extraño!';
    }

}
let button= document.getElementById('Smooth');
let hue = 0;

function animatedRainbow() {
    hue += 2;
    button.style.background =`linear-gradient(45deg,
    hsl(${hue}, 100%, 50%), 
    hsl(${hue + 60}, 100%, 50%),
    hsl(${hue + 120}, 100%, 50%))`;

    setTimeout(animatedRainbow, 50);
}
animatedRainbow();
console.log(document.getElementById('Smooth'));
