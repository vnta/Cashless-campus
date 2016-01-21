<h1>MESS AUTOMATION</h1>




<h><i>Enter roll no. to check bill<h3><br><br>
<form>
Roll No<input type="text" name="Roll"/>
<input type="button" onclick="check(this.form)" value="Login"/>
<input type="reset" value="Cancel"/>
</form>
<script language="javascript">

function check(form) /*function to check userid & password*/
{
 /*the following code checkes whether the entered userid and password are matching*/
 if(form.Roll.value >12000 && form.Roll.value<12831)
  {
   var path = form.Roll.value;
    window.open("http://172.24.9.207/12810.php ");
     }
	else
	{
	alert("Error Password or Username")/*displays error message*/
	}
	}
</script>




<style type="text/css">
h1{color:#2A1CEE;
	font-weight: 300;
	font-size: 2.5em;}
p{color:white;}
body{margin: 30px;
	padding: 50px;
	background: #0D070E;
	font-family: 'Open Sans', sans-serif;
	font-size: 10pt;
	color: #B0B0B0;}
</style>
<h2>TEAM MEMBERS</h3>
<ul>
<li>Kevin Jose</li>
<li>Avi Singh</li>
<li>Vineet Anand</li>
<li><i><b>Prawaal Pandey</b></i></li>
</ul>
<a href="https://www.facebook.com/messauto"> <img src="fb.png" alt="Facebook_connect" width="50" height="50" ></a>


