<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Projet indexation multimédia</title>
<link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body>
<?php
if(isset($_POST['exec']))
{
  if(isset($_GET['action']) && $_GET['action'] == 'yes')
  {
    exec('echo "coucou"', $output);
    print_r($output);
  }
}
echo'<div class="container">
	<section id="content">
		<form action="script.php?action=yes" method="post" id="form1">
			<h1>Classification d\'une image quelconque</h1>
			<div>
				<label>Choix du type d\'image :
				<INPUT type= "radio" name="typeI" value="url" onClick ="javascript:controle()"> url
				<INPUT type= "radio" name="typeI" value="fichier" onClick ="javascript:controle()"> fichier
				</label>
			</div>
			<div>
				<input type="text" placeholder="Url de l\'image" name="champUrl" id="champUrl" required="" />
				<input type="file" name="parcourir" id="parcourir" />
			</div>
			<div>
				<label>Recherche par :<br/>
				<INPUT type= "radio" name="typeR" value="couleur"> couleur
				<INPUT type= "radio" name="typeR" value="texture"> texture
				<INPUT type= "radio" name="typeR" value="combinaison" checked> combinaison des deux
				</label>
			</div>
			<div>
				<input type="submit" name="exec" value="Résultat" />
			</div>
		</form><!-- form -->
	</section><!-- content -->
</div><!-- container -->';
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
