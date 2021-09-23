pipeline {
    agent any

    options {
        timestamps() // Add timestamps to logging
        timeout(time: 1, unit: 'HOURS') // Abort pipleine
	
        buildDiscarder(logRotator(numToKeepStr: '8', artifactNumToKeepStr: '8'))
        disableConcurrentBuilds()
    }

    parameters {
        booleanParam(name: 'RunTestManager', defaultValue: true, description: 'Run all Test Manager tests?')
    }
    
    stages {

        stage('Init') {
            steps {
                echo 'Stage: Init'
                echo "branch=${env.BRANCH_NAME}, RunTestManager=${params.RunTestManager}"
                sh """
                ssh -V
                # java -version
                # mvn --version
                g++ --version
                """
            }
        }
        stage('Build') {
            when {
                anyOf {
                    branch 'master'
                    branch 'main'
                }
            }
            steps {
                echo 'Stage: Build'
                sh """
                make clean-all || true
                make
                """
            }
        }
        stage('Test Manager') {
            when {
                expression {
                    // BRANCH_NAME == 'master'
                    params.RunTestManager == true
                }
            }
            //options {
            //    timeout(time: 20, unit: 'MINUTES')
            //}
            steps {
                echo 'Stage: Test Manager'
                echo 'Triggering TM'
                build(job: '/TestMgrRunOne/main', parameters: [string(name: 'TestName', value: "SomeTestName")], wait: true)
            }
        }
        stage('Cleanup') {
            steps {
                echo 'Stage: Cleanup'
            }
        }

    }
    post {
        always {
            echo "post/always"
            deleteDir() // clean workspace
        }
        success {
            echo "post/success"
        }
        failure {
            echo "post/failure"
        }
    }
}
