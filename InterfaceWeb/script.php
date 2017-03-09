<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Projet indexation multimédia</title>
<link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body>

<?php
//Formulaire html
echo'<div class="container">
	<section id="content">
		<form action="script.php?action=yes" method="post" id="form1" enctype="multipart/form-data">
			<h1>Classification d\'une image</h1>
			<div>
				<label>Choix du type d\'image :<br/>
				<INPUT type= "radio" name="typeI" value="url" onClick ="javascript:controle()"> url
				<INPUT type= "radio" name="typeI" value="fichier" onClick ="javascript:controle()"> fichier
				</label>
			</div>
			<div>
				<input type="text" placeholder="Url de l\'image" name="champUrl" id="champUrl" required="" />
				<input type="file" name="userfile" id="parcourir" />
			</div>
			<div>
				<label><br/>Recherche par :<br/>
				<INPUT type= "radio" name="typeR" value="couleur"> couleur
				<INPUT type= "radio" name="typeR" value="texture"> texture
				<INPUT type= "radio" name="typeR" value="combinaison"> combinaison des deux
				</label>
			</div>
			<div>
				<input type="submit" name="exec" value="Résultat" />
			</div>
		</form><!-- form -->
	</section><!-- content -->
</div><!-- container -->';

//Lancement des scripts shell pour la classification de l'image
if(isset($_POST['exec'])){
  	if(isset($_GET['action']) && $_GET['action'] == 'yes'){
		if ($_POST['typeI'] == 'url'){ //si l'image est fournie sous forme d'url
			$url = $_POST['champUrl'];
			$tokens = explode("/", $url);
			$img = end($tokens);
			exec("sh getImgFromUrl.sh $url $img"); //téléchargement de l'image
			sleep(1);
			if ($_POST['typeR'] == 'combinaison')
				exec("sh src/classificationFusion.sh $img");
			else if ($_POST['typeR'] == 'couleur')
				exec("sh src/classificationColor.sh $img");
			else if ($_POST['typeR'] == 'texture')
				exec("sh src/classificationSift.sh $img");
		}
		else if ($_POST['typeI'] == 'fichier'){ //si l'image est fournie sous forme de fichier
			$uploaddir = 'uploads/';
			$img = $uploaddir . basename($_FILES['userfile']['name']);
			move_uploaded_file($_FILES['userfile']['tmp_name'], $img); //upload de l'image
			if ($_POST['typeR'] == 'combinaison')
				exec("sh src/classificationFusion.sh $img");
			else if ($_POST['typeR'] == 'couleur')
				exec("sh src/classificationColor.sh $img");
			else if ($_POST['typeR'] == 'texture')
				exec("sh src/classificationSift.sh $img");
		}
	}
}
sleep(7);
$file='test/result.txt'; //fichier contenant le résultat de la classification pour l'image demandée
$contenu=file_get_contents($file);
echo "<table style='margin-left:auto;margin-right:auto;'><tr><td><img src='$img' style='width:350px; height:300px;'></td> 
<td style='text-align:center;'>Classification des concepts (du plus probable au moins probable) :<br><pre>$contenu</pre></td></tr></table>";
?>
</body>
</html>

<SCRIPT LANGUAGE="javascript">
function controle() {
	if(form1.typeI[0].checked){
		form1.parcourir.style.display = "none";
		form1.champUrl.style.display = "block";
	}
	if(form1.typeI[1].checked){
		form1.parcourir.style.display = "block";
		form1.champUrl.style.display = "none";
	}
}
</SCRIPT>
