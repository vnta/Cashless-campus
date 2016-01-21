<?php
$timestamp = time();
localtime($timestamp);
print_r(localtime());
echo "<br><br>";
print_r(localtime(time(),true));
?>