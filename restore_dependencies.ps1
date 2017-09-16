Function Download-PanSEU()
{
    param([string]$Src,[string]$Des);
    $link = [regex]::match($Src,"https://pan.seu.edu.cn/#/link/(.*)").Groups[1].Value;
    $uri = "https://pan.seu.edu.cn/openapi/efshttp/v1/link?method=osdownload&userid=&tokenid=";
    $body = '{0}"link":"{1}","password":null,"reqhost":"pan.seu.edu.cn","usehttps":true{2}' -f "{",$link,"}";
    $response = Invoke-RestMethod -Uri $uri -ContentType "application/json" -Method "POST" -Body $body;
    
    $downloadUri = $response.authrequest[1];
    Invoke-RestMethod -Uri $downloadUri -Method "GET" -OutFile $Des;
    Unblock-File $Des;
}

$src = "https://pan.seu.edu.cn/#/link/58C4D436EFE24B1405861915C48B9A76";
$des = "./EGE.zip";

if (!(Test-Path ./EGE)) 
{
    if (!(Test-Path ./EGE.zip))
    {
        Download-PanSEU -Src $src -Des $des
    }
    Expand-Archive ./EGE.zip -DestinationPath ./EGE
    Remove-Item ./EGE.zip
}

if (!(Test-Path ./nlohmann_json))
{
    mkdir nlohmann_json
}

if (!(Test-Path ./nlohmann_json/json.hpp))
{
    $downloadUri = "https://github.com/nlohmann/json/releases/download/v2.1.1/json.hpp"
    $des = "./nlohmann_json/json.hpp"
    Invoke-RestMethod -Uri $downloadUri -Method "GET" -OutFile $des;
    Unblock-File $des;
}
