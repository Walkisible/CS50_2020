var modal_02 = document.getElementById("myModal_02");

var img02 = document.getElementById("myImg02");
var modalImg02 = document.getElementById("img02");
var captionText02 = document.getElementById("caption02");
var span02 = document.getElementsByClassName("close02")[0];

img02.onclick = function(){
    modal_02.style.display = "block";
    modalImg02.src = this.src;
    captionText02.innerHTML = this.alt;
}

span02.onclick = function(){
    modal_02.style.display = "none";
}
