#!/usr/bin/perl -w use strict;
use warnings;
use HTTP::Request; use HTTP::Headers; use LWP::UserAgent; use JSON::PP;
my $ua = LWP::UserAgent->new(ssl_opts => { SSL_verify_mode => 'SSL_VERIFY_NONE' }j;
sub command{
my($host, $target, $method, $header_ref, $data_ref) = @_;
my $data_json = %{$data_ref} ? encode_json($data_ref) : "";
my $request = HTTP::Request->new($method => 
   "https://$host:7443/$target", HTTP::Headers->new(%{$header_ref}), $data_json);
$request->header(Content_Type => 'application/json');
my $response = $ua->request($request);
return decode_json($response->content);
}