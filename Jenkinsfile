#!/usr/bin/env groovy

@Library('jenkinstools@v4.0.0')
import de.testo.jenkinstools.*
import org.jenkinsci.plugins.workflow.steps.FlowInterruptedException


def numBuildsToKeep = '5'
def branch = BRANCH_NAME

def canceldExceptionOcucred = false

def containerImagePath = "docker.testo.dev/ci-cpp-base:v3.5.0"

if(branch.startsWith('MR-')) {
    numBuildsToKeep = '3'
    branch = env.CHANGE_BRANCH
    echo "Merge request from " + env.CHANGE_BRANCH + " to " + env.CHANGE_TARGET
}

properties([
    [
    $class: 'BuildDiscarderProperty',
    strategy: [$class: 'LogRotator', artifactDaysToKeepStr: '', artifactNumToKeepStr: '', daysToKeepStr: '', numToKeepStr: numBuildsToKeep]
    ],
    [$class: 'JobInclusionJobProperty', jobGroupName: 'under_construction', useJobGroup: true]
])
abortPreviousRunningBuilds()



try {
    String strProjectGitURL = "git@gitlab.cds.testo:third_party/freertos.git"
    
    def waitForAndPropagateUiTest = false
    if(branch.startsWith('MR-')) {
        waitForAndPropagateUiTest = true
        branch = env.CHANGE_BRANCH
        echo "Merge request from " + env.CHANGE_BRANCH + " to " + env.CHANGE_TARGET
    }

     // define build matrix
    def build_configurations_cmake_presets = [
        windows: [
            RUN_UNIT_TESTS: "TRUE",
            ARCH: "amd64",
            BTYPE: ["rel","dbg"],
            COMP: ["msvc17"],
            LTYPE: "shared",
            TARGET_SYSTEM: "windows",
            SYSTEM: "windows",
            CMAKE_GENERATOR: "Visual Studio",
            PRESET_PREFIX: ["windows-base_multiConfig"],
        ],
        
        linux: [
            ARCH: "amd64",
            BTYPE: ["rel","dbg"],
            COMP: "gcc-10",
            FRAMEBUFFER: "Xvfb",
            LTYPE: "shared",
            SYSTEM: "linux",
            CMAKE_GENERATOR: "Ninja",
            CONTAINER: "${containerImagePath}",
            CONTAINER_CPU_REQUEST: "6",
            USE_LINKER_LLD: "true",
            ENABLE_GCOV: 'false',
            GCOVR_INCLUDE_FOLDERS: 'freertos',
            WORKSPACE: '/home/jenkins/agent/workspace/FreeRTOS/',
            PRESET_PREFIX: ["linux-base_multiConfig"]
        ]
    ]

    

    def universalEnvironment = [
        APP_EXTENSIONS: "_development_status",
        PROJNAME: "FreeRTOS",
        USE_CCACHE: "true",
        DISABLE_STORING_OF_ARTIFACTS: "true",
        USE_DEFAULT_CONFIG: "true",
        MAKE_INSTALL: "true",
        STATIC_ANALYZER: "none",
        GCOVR_THRESHOLD_HEALTHY: "0",
        GCOVR_THRESHOLD_UNSTABLE: "0", //unhealty builds will not merge automatically
        GCOVR_THRESHOLD_UNHEALTY: "0", //unhealty builds will fail
        QT_VERSION: "5.15.8",
        RUN_UNIT_TESTS: "TRUE"
    ]

    String defaultExcludeList =  "t3xx_2025/modules/FreeRTOS " +
                                                            "t3xx_2025/modules/t300Generated " +
                                                            "t3xx_2025/modules/tinyxml "
    
    

    
    stage('presets_and_legacy_build') {
        
        buildCommandPresets = {
            timestamps {
                timeout(20) {
                    printNodeName()
                    checkoutGit("${strProjectGitURL}", branch, "FreeRTOS")
                    printEnv()
                }
                timeout(60) {
                    println("CMAKE Generator Value is $CMAKE_GENERATOR")
                    println("Preset Prefix Name is $PRESET_PREFIX")
                    try {
                        cmakePresetsConfigureBuildTest(PRESET_PREFIX, BTYPE)
                        //Tests currently not active
                        //xunit([GoogleTest(excludesPattern: '', failIfNotNew: false, pattern: 'testresults/*.xml', skipNoTestFiles: true, stopProcessingIfError: true)])
                    }
                    finally {
                        if(env['SYSTEM'] != 'windows')
                        {
                            sh "ccache -s -v"
                        }
                    }
                }
            }
        }

        def buildMatrixPresets = new ContainerBuildMatrix(build_configurations_cmake_presets, universalEnvironment, this)
        def buildMatrixMapPresets = buildMatrixPresets.getSubtasks(buildCommandPresets)

        parallel buildMatrixMapPresets
    }
    
}

catch (FlowInterruptedException interruptEx) 
{
    println "canceled exception"
    currentBuild.result = 'FAILURE'
    canceldExceptionOcucred = true;
}
catch(Exception e)
{
    println("Undefined exception ouccred...failed")
    currentBuild.result = 'FAILURE'
    printException(e)
    throw e
}
finally
{
    println("finnsished runnung pipeline")
    // Send notifications for develop and *automerge* branches
    if(!canceldExceptionOcucred) {
    }
}
