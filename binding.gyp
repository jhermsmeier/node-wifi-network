{
  "targets": [
    {
      "target_name": "wlan",
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "sources": [
        "src/wlan.cpp"
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
