<?php

$user="root";
$password="";
$database="test";

$con = mysql_connect(localhost,$user,$password);
echo $con;
mysql_select_db($database);

$query="CREATE TABLE sensor1 (id int(6) NOT NULL auto_increment,entryCount varchar(15) NOT NULL,timecreate datetime,PRIMARY KEY (id),UNIQUE id (id),KEY id_2 (id))";

echo mysql_query($query, $con);
mysql_close();

?>