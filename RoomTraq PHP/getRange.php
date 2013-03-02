<?php

//GET
$start=$_GET['start'];
$end=$_GET['end'];

//DATABASE CODE
$user="root";
$password="";
$database="roomtraq";
$con = mysql_connect('localhost',$user,$password);
mysql_select_db($database);

$from_date = $start;
$to_date = $end;

$result = mysql_query("SELECT * FROM sensor1 WHERE timestamp >= '" . $from_date . "' AND timestamp <= '" . $to_date . "' ORDER by id DESC",$con);

$config['table_name'] = "sensor1";
$xml          = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
$root_element = $config['table_name'];
$xml         .= "<$root_element>";

 
if(mysql_num_rows($result)>0)
{
   while($result_array = mysql_fetch_assoc($result))
   {
      $xml .= "<value>";
 
      //loop through each key,value pair in row
      foreach($result_array as $key => $value)
      {
         //$key holds the table column name
         $xml .= "<$key>";
 
         //embed the SQL data in a CDATA element to avoid XML entity issues
         $xml .= "$value"; 
 
         //and close the element
         $xml .= "</$key>";
      }
 
      $xml.="</value>";
   }
}

//close the root element
$xml .= "</$root_element>";
 
//send the xml header to the browser
header ("Content-Type:text/xml"); 
 
//output the XML data
echo $xml;

?>