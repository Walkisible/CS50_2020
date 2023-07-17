var modal_01 = document.getElementById("myModal_01");

var img01 = document.getElementById("myImg01");
var modalImg01 = document.getElementById("img01");
var captionText01 = document.getElementById("caption01");
var span01 = document.getElementsByClassName("close01")[0];

img01.onclick = function(){
    modal_01.style.display = "block";
    modalImg01.src = this.src;
    captionText01.innerHTML = this.alt;
}

span01.onclick = function(){
    modal_01.style.display = "none";
}
