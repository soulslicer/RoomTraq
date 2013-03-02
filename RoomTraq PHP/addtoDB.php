<?php

//GET
$count=$_GET['count'];

//DATABASE CODE
$user="root";
$password="";
$database="RoomTraq";
$con = mysql_connect('localhost',$user,$password);
mysql_select_db($database);
//echo $con;

//TIME
date_default_timezone_set('Asia/Singapore'); // CDT
$info = getdate();
$date = $info['mday'];
$month = $info['mon'];
$year = $info['year'];
$hour = $info['hours'];
$min = $info['minutes'];
$sec = $info['seconds'];
$current_date = "$year-$month-$date $hour:$min:$sec";
$formatted_date = sprintf("%04d-%02d-%02d %02d:%02d:%02d", $year, $month, $date,$hour,$min,$sec);


//2013-02-24 23:37:54
$query = "INSERT INTO sensor1 VALUES ('','$count','$formatted_date')";
echo "(";

mysql_query($query, $con);

mysql_close();

?>