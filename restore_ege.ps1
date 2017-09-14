Function Download-PanSEU()
{
    param([string]$Src,[string]$Des);
    $link = [regex]::match($Src,"https://pan.seu.edu.cn/#/link/(.*)").Groups[1].Value;
    $uri = "https://pan.seu.edu.cn/openapi/efshttp/v1/link?method=osdownload&userid=&tokenid=";
    $body = '{0}"link":"{1}","password":null,"reqhost":"pan.seu.edu.cn","usehttps":true{2}' -f "{",$link,"}";
    $response = Invoke-RestMethod -Uri $uri -ContentType "application/json" -Method "POST" -Body $body;
    
    $downloadUri = $response.authrequest[1];
    $webClient = new-object System.Net.WebClient;
    $webClient.DownloadFile($downloadUri, $Des);
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

