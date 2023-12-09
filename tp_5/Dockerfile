# Utiliser l'image de Tomcat comme base
FROM tomcat:latest

# Copier l'archive WAR de Jenkins dans le répertoire webapps de Tomcat
COPY jenkins.war /usr/local/tomcat/webapps/jenkins.war

# Exposer le port 8080
EXPOSE 8080
