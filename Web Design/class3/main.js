//alert("Alert from main.js")
/*
window.onload=function(){
    document.onclick=function(e){
        alert(e.target.innerHTML+"有"+e.target.innerHTML.length+"個字元");
        console.log(e);
    }
}*/

/*
let confirmAnswer =confirm("你真的確定你想要取消這個服務嗎?")
let thisH1=document.getElementsByTagName("h1")[0];
if(confirmAnswer){
    thisH1.innerHTML="服務已取消";
}else{
    thisH1.innerHTML="繼續使用本服務";
}*/

/*
let promptAnswer=prompt("小明家裡有三個小孩，他兩個哥哥叫張一和張二，請問第三個小孩叫甚麼?","張三");
let thisH1=document.getElementById("Response");

switch(promptAnswer){
    case "張三":
        thisH1.innerHTML="那小明是誰?";
        break;
    case "小明":
        thisH1.innerHTML="聰明";
        break;
    default:
        thisH1.innerHTML="你想多了";
}*/

function showAlert(){
    thisH1.innerHTML="Hello!";
}

let thisButton=document.getElementsByTagName("Button")[0];
let thisH1=document.getElementById("h1")[0];
thisButton.onclick=function(){
    showAlert();
    //thisH1.innerHTML="Hello!";
};