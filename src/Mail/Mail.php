<?PHP
/*
    Nombre: Mail.php
    Autor: Julio Tuozzo
    Función: Clase que maneja el envío de e-mails
    Fecha de creación: 23/05/2025.
    Ultima modificación: 28/01/2026.
*/

namespace App\Mail;

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\SMTP;
use PHPMailer\PHPMailer\Exception;

class Mail extends PHPMailer
	{public function sendMail($e_mail,$subject,$mensaje)
			{// Envío el correo

			 $this->ClearAllRecipients();
			 $this->IsSMTP();
			 $this->Port= MAIL_PORT;
			 $this->Host = MAIL_HOST;
			 $this->SMTPAuth = true;
			 $this->Username = MAIL_USUARIO;
			 $this->Password = MAIL_CLAVE;
			 $this->CharSet = 'UTF-8';

			 $this->SMTPDebug = 0;

			//  Agregar este código cuando no conecta en SSL

			 $this->SMTPOptions = array(
				'ssl' => array(
					'verify_peer' => false,
					'verify_peer_name' => false,
					'allow_self_signed' => true
				)
			 );


			// */

			 $this->From = MAIL_USUARIO;
			 $this->FromName = MAIL_REMITENTE;

			 // $e_mail puede ser un array de direcciones o una única dirección

			 if(is_array($e_mail))
			 	{foreach($e_mail as $este_mail)
					{$this->AddAddress($este_mail);
					}
				}
			 else
			 	{$this->AddAddress($e_mail);
			 	}


			 $this->IsHTML(true);

			 $this->Subject = $subject;

			 $mensaje = "<div style='text-align:left'><img style='text-align:center' src='cid:MDML' alt='Mercado Dios Me Libre' border=0 /></div>
				<br /> <br />$mensaje ";


			 $mensaje.="<br /> <br /> <em> <strong>Este mensaje fue enviado desde una casilla sin atenci&oacute;n, no responda al remitente. </strong> </em><br /><br />&nbsp;";



			  $this->Body = $mensaje;

			  $this->AddEmbeddedImage("./images/logo_mail.png", "MDML", "logo_mail.png", "base64", "image/png");



			 if($this->Send())
	                     {return true;
	                     }
                else
                     {$mensaje=strip_tags(html_entity_decode($mensaje,ENT_QUOTES,'UTF-8'));
          		      $error=strip_tags(html_entity_decode($this->ErrorInfo,ENT_QUOTES,'UTF-8'));
  		  	          $fecha=date("d/m/Y H:i:s");

					  if(is_array($e_mail))
							{$los_e_mail="";
							 foreach($e_mail as $el_mail)
								{$los_e_mail.=$el_mail.", ";
								}
							}
					  else
							{$los_e_mail=$e_mail;
							}



$error_msg="Fecha: $fecha
From: <{$this->From}> {$this->FromName}
To: <$los_e_mail>
Subject: $subject
Mensaje:
$mensaje

Mensaje de error: $error
==================================================================================================

";
                      file_put_contents(LOGS."email_error_log.txt", $error_msg, FILE_APPEND | LOCK_EX);
                      return false;
                     }

		    }

	}
?>
