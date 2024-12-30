from http.server import HTTPServer, SimpleHTTPRequestHandler

class CSPRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        # Add Content Security Policy (CSP) header with 'unsafe-eval'
        self.send_header(
            "Content-Security-Policy",
             "script-src 'self' 'unsafe-eval' 'unsafe-inline';"
        )
        # Add other security headers for protection
        self.send_header("X-Content-Type-Options", "nosniff")
        self.send_header("X-Frame-Options", "DENY")
        super().end_headers()

if __name__ == "__main__":
    # Define the server address and port
    server_address = ("", 8000)  # Listen on all interfaces, port 8000
    httpd = HTTPServer(server_address, CSPRequestHandler)
    print("Serving on port 8000 with unsafe-eval enabled...")
    httpd.serve_forever()
