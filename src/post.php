<?php
$sname = "localhost";
$uname = "ababdelo";
$password = "Thewayofthemakersis 1337";
$db_name = "LE3TMAKERS";

$api_key_value = "483f2f4bc98c7dbb9adb6bf693881c0e";

$api_key = $username = $uid = $role = $action  = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if ($api_key == $api_key_value) {
        $username = test_input($_POST["username"]);
        $uid = test_input($_POST["uid"]);
        $role = test_input($_POST["role"]);
        $action = test_input($_POST["action"]);

        // Create connection
        $conn = new mysqli($sname, $uname, $password, $db_name);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        $sql = "INSERT INTO Activity (username, uid, role, action)
        VALUES ('" . $username . "', '" . $uid . "', '" . $role . "', '" . $action . "')";

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
