</pre>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
 <html xmlns="http://www.w3.org/1999/xhtml">
 <head>
 <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
 <title>My Site</title>
 <style type="text/css">
 <!--
 .style1 {color: #FF0000}
 -->
 </style>
 </head>
 <body>
 <?php
 include_once('db_connect.php');
 echo 'Connection Successfull<br>';
 $Result=mysql_db_query('student_rec','SELECT NAME,ROLL_NO FROM student_personal');
 echo "<table width="200" border="1">";
 echo "<tr> <td><strong><span class="style1">Name</span></strong></td> <td><strong>Roll No.</strong></td></tr>";
 while($row=mysql_fetch_array($Result))
 {
 echo "<tr>";
 echo "<td>".$row["NAME"]."</td>"."<td>".$row["ROLL_NO"]."</td>";
 echo "</tr>";
 }
 echo "</table>";
 ?>
 </body>
 </html>
<pre>