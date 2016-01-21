<html>

	<head>
	<title> Coupons</title>
	<link href="css/styles.css" media="screen" rel="stylesheet" type="text/css" />
	</head>
	
	<body>
	<div id="page">
		<div id="site_title">
			<span>COUPONS AVAILABLE IN THE MESS</span>
		</div>
		
		<div id="primary_content">
			
			<div id="page_content">
			
			
				<h2>List of Coupons</h2>
				</div>
					<?php
					
					echo '<table border="1">';
					echo '<tr>';
					echo '<th>Coupon</th>';
					echo '<th>Price</th>';
					echo '<tr>';

					
					
					
					
					
					$con=mysqli_connect("localhost","root","","final_db");
					// Check connection
					if (mysqli_connect_errno())
					{
					echo "Failed to connect to MySQL: " . mysqli_connect_error();
					}

					$result = mysqli_query($con,"SELECT * FROM coupon ORDER BY Coupon_price");

					while($row = mysqli_fetch_array($result))
								  {
										echo '<tr>';
										echo '<td>', $row['Copon_name'], '</td>';
										echo '<td>', $row['Coupon_price'], '</td>';
										echo '<tr>';
										
									}
									echo '</table>';

							
					

						
					mysqli_close($con);

					?>
					
					
					<form action="update_price.php" method="post">
					Coupon name: <input type="text" name="Name">
                    Coupon price <input type="text" name="price">

                    <input type="submit" value="Change price"></p></b></h2>
                       
					</form>
					<br>

					


		</div>
	</div>
</body>

</html>