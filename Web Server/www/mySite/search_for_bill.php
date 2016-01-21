<html>

	<head>
	<title> Bill Page</title>
	<link href="css/styles.css" media="screen" rel="stylesheet" type="text/css" />
	</head>
	
	<body>
	<div id="page">
		
		<div id="primary_content">
			
			<div id="page_content">
				</div>
				
<?php
$con=mysqli_connect("localhost","root","","bill_db");
// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  
$value=$_GET['Roll'];
$result = mysqli_query($con,"SELECT * FROM bill
WHERE Roll='$value'");

while($row = mysqli_fetch_array($result))
  {
  echo "The bill for Roll Number: ";
  echo $row['Roll'] . " is Rs. " . $row['Bill'];
  echo "<br>";
  }

mysqli_close($con);
?>


		</div>
	</div>
</body>

</html>