<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="5" >
    <link rel="stylesheet" type="text/css" href="../style/style.css" media="screen"/>

	<title> Activity Logger</title>

</head>

<body>
    <h1>Activity Logger</h1>
<?php
$sname = "localhost";
$uname = "ababdelo";
$password = "Thewayofthemakersis 1337";
$db_name = "LE3TMAKERS";

// Create connection
$conn = new mysqli($sname, $uname, $password, $db_name);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, username, uid, role, action, time FROM Activity ORDER BY id ASC"; /*select items to display from the Activity table in the data base*/

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <th>ID</th> 
        <th>Username</th>
        <th>UID</th>
        <th>Role</th>
        <th>Action</th>
        <th>Time</th>
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $id = $row["id"];
        $uname = $row["username"];
        $uid = $row["uid"];
        $role = $row["role"];
        $action = $row["action"];
        $time = $row["time"];
        
        echo '<tr> 
                <td>' . $id . '</td>
                <td>' . $uname . '</td>
                <td>' . $uid . '</td>
                <td>' . $role . '</td>
                <td>' . $action . '</td>
                <td>' . $time . '</td>
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>

</body>
</html>