<html>
<?php
$hour = date('h');
        //if ($hour > 7 && $hour < 11) {
              echo $hour;  
        /*} if ($hour > 12 && $hour < 18) {
               echo "Lunch time";
        } if($hour > 19 && $hour < 22) {
               echo "dinner time" ; 
        }*/
		echo"<br>";
		
$t=time();
echo($t . "<br>");
echo(date("Y-m-d",$t));
?>
</html>