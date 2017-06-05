{
  "targets": [
    {
      "target_name": "wifi",
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "sources": [
        "src/wifi.cpp",
        "src/wifi-scan.cpp",
        "src/wifi-network.cpp",
        "src/wifi-interface.cpp"
      ],
      "conditions": [
        [ 'OS=="mac"', {
          "sources": [
            "src/darwin/corewlan.mm"
          ],
          "link_settings": {
            "libraries": [
              "CoreWLAN.framework"
            ]
          }
        }],
        [ 'OS=="win"', {
          "sources": [
            "src/windows/nativewifi.cpp"
          ],
          "libraries": [
            "-lwlanapi.lib",
            "-lole32.lib"
          ]
        }],
        [ 'OS=="linux"', {
          "sources": []
        }]
      ]
    }
  ]
}
