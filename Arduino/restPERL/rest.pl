#!/usr/bin/perl
package ClientRest;
use REST::Client;
 
my $client = REST::Client->new();

$client->addHeader('Content-Type', 'application/json');
$client->addHeader('charset', 'UTF-8');
$client->addHeader('Accept', 'application/json');

$req = '{
	"gateway_id" : "A0001-99",
		"password" : "abcdef",
			"transaction_type" : "00",
				"cc_number" : "4111111111111111",
					"cc_expiry":"1019",
						"amount":"20.75",
							"cardholder_name": "Donald Duck"
								}';

								#If using a live account
								##$url="https://api.e-xact.com/transaction";
								#
								##If using a demo account in the E-xact Demo Environment 
								#$url="https://api.demo.e-xact.com/transaction"; 
								#
								#$client->POST($url, $req);
								#print $client->responseContent();
								# 
								# #response headers may be gathered
								# print $client->responseHeader('ResponseHeader');
