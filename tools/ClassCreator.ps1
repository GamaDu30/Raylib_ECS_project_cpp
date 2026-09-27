Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

[System.Windows.Forms.Application]::EnableVisualStyles()

# --------------------------------------------------
# Configuration
# --------------------------------------------------

$ProjectRoot = Split-Path -Parent $PSScriptRoot

# --------------------------------------------------
# Fonctions
# --------------------------------------------------

function New-CppClass {
    param (
        [string]$ClassName,
        [string]$Folder,
        [string]$Namespace
    )

    if ([string]::IsNullOrWhiteSpace($ClassName)) {
        [System.Windows.Forms.MessageBox]::Show(
            "Nom de classe vide.",
            "Erreur"
        )
        return
    }

    # Autorise uniquement noms C++ classiques
    if ($ClassName -notmatch '^[A-Za-z_][A-Za-z0-9_]*$') {
        [System.Windows.Forms.MessageBox]::Show(
            "Nom de classe invalide.",
            "Erreur"
        )
        return
    }

    if ([string]::IsNullOrWhiteSpace($Folder)) {
        [System.Windows.Forms.MessageBox]::Show(
            "Sélectionne un dossier.",
            "Erreur"
        )
        return
    }

    if (-not (Test-Path $Folder -PathType Container)) {
        [System.Windows.Forms.MessageBox]::Show(
            "Dossier introuvable.",
            "Erreur"
        )
        return
    }

    $HppPath = Join-Path $Folder "$ClassName.hpp"
    $CppPath = Join-Path $Folder "$ClassName.cpp"

    if ((Test-Path $HppPath) -or (Test-Path $CppPath)) {
        [System.Windows.Forms.MessageBox]::Show(
            "Un des fichiers existe déjà.",
            "Erreur"
        )
        return
    }

    # --------------------------------------------------
    # Génération du header
    # --------------------------------------------------

    $HeaderContent = @"
#pragma once

class $ClassName
{
public:
    $ClassName();
    ~$ClassName();
};

"@

    # --------------------------------------------------
    # Génération du cpp
    # --------------------------------------------------

    $CppContent = @"
#include "$ClassName.hpp"

$ClassName::$ClassName()
{
}

$ClassName::~$ClassName()
{
}

"@

    # Namespace optionnel
    if (-not [string]::IsNullOrWhiteSpace($Namespace)) {

        $HeaderContent = @"
#pragma once

namespace $Namespace
{
    class $ClassName
    {
    public:
        $ClassName();
        ~$ClassName();
    };
}

"@

        $CppContent = @"
#include "$ClassName.hpp"

namespace $Namespace
{
    $ClassName::$ClassName()
    {
    }

    $ClassName::~$ClassName()
    {
    }
}

"@
    }

    # --------------------------------------------------
    # Écriture fichiers
    # --------------------------------------------------

    Set-Content `
        -Path $HppPath `
        -Value $HeaderContent `
        -Encoding utf8

    Set-Content `
        -Path $CppPath `
        -Value $CppContent `
        -Encoding utf8

    # Ouvre les fichiers avec VS Code
    code "$HppPath"
    code "$CppPath"
}

# --------------------------------------------------
# Interface graphique
# --------------------------------------------------

$form = New-Object System.Windows.Forms.Form

$form.Text = "New C++ Class"
$form.Size = New-Object System.Drawing.Size(500, 300)
$form.StartPosition = "CenterScreen"
$form.FormBorderStyle = "FixedDialog"
$form.MaximizeBox = $false
$form.MinimizeBox = $false

# Nom classe
$labelClass = New-Object System.Windows.Forms.Label
$labelClass.Text = "Class name:"
$labelClass.Location = New-Object System.Drawing.Point(20, 25)
$labelClass.AutoSize = $true

$textClass = New-Object System.Windows.Forms.TextBox
$textClass.Location = New-Object System.Drawing.Point(150, 22)
$textClass.Size = New-Object System.Drawing.Size(300, 25)

# Dossier
$labelFolder = New-Object System.Windows.Forms.Label
$labelFolder.Text = "Folder:"
$labelFolder.Location = New-Object System.Drawing.Point(20, 70)
$labelFolder.AutoSize = $true

$textFolder = New-Object System.Windows.Forms.TextBox
$textFolder.Location = New-Object System.Drawing.Point(150, 67)
$textFolder.Size = New-Object System.Drawing.Size(220, 25)
$textFolder.Text = Join-Path $ProjectRoot "src"

$buttonBrowse = New-Object System.Windows.Forms.Button
$buttonBrowse.Text = "Browse..."
$buttonBrowse.Location = New-Object System.Drawing.Point(380, 65)
$buttonBrowse.Size = New-Object System.Drawing.Size(70, 28)

$buttonBrowse.Add_Click({

    $dialog = New-Object System.Windows.Forms.FolderBrowserDialog

    $dialog.SelectedPath = $textFolder.Text

    if ($dialog.ShowDialog() -eq "OK") {
        $textFolder.Text = $dialog.SelectedPath
    }
})

# Namespace
$labelNamespace = New-Object System.Windows.Forms.Label
$labelNamespace.Text = "Namespace:"
$labelNamespace.Location = New-Object System.Drawing.Point(20, 115)
$labelNamespace.AutoSize = $true

$textNamespace = New-Object System.Windows.Forms.TextBox
$textNamespace.Location = New-Object System.Drawing.Point(150, 112)
$textNamespace.Size = New-Object System.Drawing.Size(300, 25)

# Bouton créer
$buttonCreate = New-Object System.Windows.Forms.Button
$buttonCreate.Text = "Create Class"
$buttonCreate.Location = New-Object System.Drawing.Point(150, 175)
$buttonCreate.Size = New-Object System.Drawing.Size(150, 40)

$buttonCreate.Add_Click({

    New-CppClass `
        -ClassName $textClass.Text `
        -Folder $textFolder.Text `
        -Namespace $textNamespace.Text
})

# Touche Entrée
$form.AcceptButton = $buttonCreate

# Ajout contrôles
$form.Controls.Add($labelClass)
$form.Controls.Add($textClass)

$form.Controls.Add($labelFolder)
$form.Controls.Add($textFolder)
$form.Controls.Add($buttonBrowse)

$form.Controls.Add($labelNamespace)
$form.Controls.Add($textNamespace)

$form.Controls.Add($buttonCreate)

# Lancement
[System.Windows.Forms.Application]::Run($form)