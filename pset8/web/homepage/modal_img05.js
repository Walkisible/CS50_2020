var modal_05 = document.getElementById("myModal_05");

var img05 = document.getElementById("myImg05");
var modalImg05 = document.getElementById("img05");
var captionText05 = document.getElementById("caption05");
var span05 = document.getElementsByClassName("close05")[0];

img05.onclick = function(){
    modal_05.style.display = "block";
    modalImg05.src = this.src;
    captionText05.innerHTML = this.alt;
}

span05.onclick = function(){
    modal_05.style.display = "none";
}
