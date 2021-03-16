<?php

exec('find . -type f -name "*.h" > list');
$files = file_get_contents('list');
$fileArray = explode("\n", $files);

foreach ($fileArray as $key => $filePath)
{
    if (empty($filePath))
    {
        return;
    }

    // echo "\n" . $filePath;
    $fileContents = file_get_contents($filePath);
    $pos = strpos($fileContents, "#pragma once");

    if (is_int($pos) && $pos === 0)
    {
        $fileNameArray = explode(DIRECTORY_SEPARATOR, $filePath);
        $fileName = $fileNameArray[ count($fileNameArray) -1 ];
        $fileName = str_replace('.', '_', $fileName);
        $fileName = strtoupper($fileName);

        // echo "\n" . $fileName . " " . $pos;

        $fileContents = str_replace(
            "#pragma once",
            "#ifndef ".$fileName."\n"."#define ".
            $fileName, $fileContents
        );
        $fileContents .= "\n\n#endif // ".$fileName;

        file_put_contents($filePath, $fileContents);
    }

}

?>