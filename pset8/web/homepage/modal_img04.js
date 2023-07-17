var modal_04 = document.getElementById("myModal_04");

var img04 = document.getElementById("myImg04");
var modalImg04 = document.getElementById("img04");
var captionText04 = document.getElementById("caption04");
var span04 = document.getElementsByClassName("close04")[0];

img04.onclick = function(){
    modal_04.style.display = "block";
    modalImg04.src = this.src;
    captionText04.innerHTML = this.alt;
}

span04.onclick = function(){
    modal_04.style.display = "none";
}
