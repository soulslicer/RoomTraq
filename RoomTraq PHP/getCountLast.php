<?php

//DATABASE CODE
$user="root";
$password="";
$database="RoomTraq";
$con = mysql_connect('localhost',$user,$password);
mysql_select_db($database);
//echo $con;

$query="SELECT * FROM sensor1";
$result=mysql_query($query);
$num=mysql_numrows($result);

$query="SELECT * FROM sensor1 where id=$num";
$result=mysql_query($query);
$count=mysql_result($result,0,"entryCount");

echo $count;

?>