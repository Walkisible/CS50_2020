var modal_03 = document.getElementById("myModal_03");

var img03 = document.getElementById("myImg03");
var modalImg03 = document.getElementById("img03");
var captionText03 = document.getElementById("caption03");
var span03 = document.getElementsByClassName("close03")[0];

img03.onclick = function(){
    modal_03.style.display = "block";
    modalImg03.src = this.src;
    captionText03.innerHTML = this.alt;
}

span03.onclick = function(){
    modal_03.style.display = "none";
}
