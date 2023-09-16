<?php
$sname = "localhost";
$uname = "ababdelo";
$password = "Thewayofthemakersis 1337";
$db_name = "databasecode";

$api_key_value = "483f2f4bc98c7dbb9adb6bf693881c0e";

$api_key = $sensor = $location = $value1 = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if ($api_key == $api_key_value) {
        $sensor = test_input($_POST["sensor"]);
        $location = test_input($_POST["location"]);
        $value = test_input($_POST["value"]);

        // Create connection
        $conn = new mysqli($sname, $uname, $password, $db_name);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        $sql = "INSERT INTO sensordata (sensor, location, value)
        VALUES ('" . $sensor . "', '" . $location . "', '" . $value . "')";

        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $conn->close();
    } else {
        echo "Wrong API Key provided.";
    }
} else {
    echo "No data posted with HTTP POST.";
}

function test_input($data)
{
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
