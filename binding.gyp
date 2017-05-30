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
        "src/wifi-network.cpp"
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
          "sources": []
        }],
        [ 'OS=="linux"', {
          "sources": []
        }]
      ]
    }
  ]
}
