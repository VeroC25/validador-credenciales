pipeline {

    agent any

    options {
        timestamps()
        timeout(time: 10, unit: "MINUTES")
        buildDiscarder(logRotator(numToKeepStr: "15"))
        disableConcurrentBuilds()
    }

    triggers {
        pollSCM("H/2 * * * *")
    }

    environment {
        VERSION = "0.1.${BUILD_NUMBER}"
    }

    stages {

        stage("Preparar") {
            steps {
                echo "Rama: ${env.BRANCH_NAME ?: env.GIT_BRANCH}"
                echo "Construyendo version ${VERSION}"
                sh "make clean"
            }
        }

        stage("Compilar") {
            steps {
                sh "make all VERSION=${VERSION}"
            }
        }

        stage("Probar") {
            steps {
                catchError(buildResult: "UNSTABLE", stageResult: "UNSTABLE") {
                    sh "make test VERSION=${VERSION}"
                }
            }
            post {
                always {
                    junit allowEmptyResults: true,
                          testResults: "build/reports/*.xml"
                }
            }
        }

        stage("Empaquetar") {
            when {
                allOf {
                    expression { (env.BRANCH_NAME ?: env.GIT_BRANCH) ==~ /(origin\/)?main/ }
                    expression { currentBuild.result == null ||
                                 currentBuild.result == "SUCCESS" }
                }
            }
            steps {
                sh "make package VERSION=${VERSION}"
            }
        }

        stage("Entregar") {
            when {
                allOf {
                    expression { (env.BRANCH_NAME ?: env.GIT_BRANCH) ==~ /(origin\/)?main/ }
                    expression { currentBuild.result == null ||
                                 currentBuild.result == "SUCCESS" }
                }
            }
            steps {
                archiveArtifacts artifacts: "build/dist/*.tar.gz",
                                 fingerprint: true
            }
        }

    }

    post {
        success  { echo "SUCCESS: version ${VERSION} verificada" }
        unstable { echo "UNSTABLE: compilo, pero fallaron pruebas" }
        failure  { echo "FAILURE: revise la consola" }
        always   { cleanWs() }
    }

}
