
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>

<script type="application/x-javascript"> 
     
   addEventListener("load", function() 
   { 
   setTimeout(updateLayout, 0); 
   }, false); 
   
   var currentWidth = 0; 
   
   function updateLayout() 
   { 
   if (window.innerWidth != currentWidth) 
   { 
   currentWidth = window.innerWidth; 
   
   var orient = currentWidth == 320 ? "profile" : "landscape"; 
   document.body.setAttribute("orient", orient); 
   setTimeout(function() 
   { 
   window.scrollTo(0, 1); 
   }, 100); 
   } 
   } 
   
   setInterval(updateLayout, 100); 
   
   </script>



<meta http-equiv="content-type" content="text/html; charset=utf-8">
<meta name="viewport" content="width=350, user-scalable=no">

<title>Wash the clothes!</title>
<link rel="stylesheet" href="dog.css" type="text/css">

<body>

<div class="round_box" id="navigation">
	<img class="round_corner" src="img/round_top_long.png">
	<div class="content">
<script>
function get(url) { 
var xmlhttp=false;
 xmlhttp = new XMLHttpRequest();
 xmlhttp.open("GET", url,true);
 xmlhttp.send(null)
}
</script>

<?php
$status = exec('/usr/bin/python /www/pages/status.py');

switch ($status){
    case 0:
        echo '<img src="img/washer_dryer.gif" width="300" height="200">';
        break;
    case 1:
        echo '<img src="img/washer_lit.gif" width="300" height="200">';
        break;
    case 2:
        echo '<img src="img/dryer_lit.gif" width="300" height="200">';
        break;
    case 3:
        echo '<img src="img/both_lit.gif" width="300" height="200">';
        break;
    }
    



#<a class="actions" href="#" onClick="get('http://192.168.10.160/reset.py'); "><img src="img/stop.jpg"></a>
?>
<center>
<a href="http://fire.homelinux.net:8080/reset.php"><img src="img/stop.jpg" width="50" height="50"></a>

<div class="clear"></div>
        </div>
        <img class="round_corner" src="img/round_bottom_long.png">
</div>


<div id="push"></div>
     </div>
<div id="footer">
     <p></p>


</body>
</html>

